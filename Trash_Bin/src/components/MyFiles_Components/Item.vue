<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import { sendUpdate } from '@/requests';
import DeleteButton from '../General_Components/DeleteButton.vue'
import TableView from './TableView.vue';
import EditableCell from './EditableCell.vue';
import TextCell from './TextCell.vue';
import { badge } from '@/tailwindClasses';

    export default defineComponent ({
        props: {
            item: Types.Item
        },
        data() {return {
            badge,
            toggle: false,
            padding: (this.item != undefined) ? this.item.depth * 30 + "px" : "0px"
        }},
        components: {
            DeleteButton,
            TableView,
            TextCell
        },
        emits: ['delete'],
        methods: {
            uploadSubmit(content: string) {
                if (this.item != null) {
                    this.item.content = content
                    this.$forceUpdate
                    sendUpdate(this.item)
                }
            }
        }
    })
</script>

<template>
    <div :style="{'padding-left':padding}">
        <span :class=badge>
            <span @click="toggle = !toggle">
                📄Name: {{ item?.name }}, Extension: {{ item?.extension }}
            </span>
            <DeleteButton @click="$emit('delete')" />
        </span>
    </div>
    <div v-if="toggle">
        <TableView v-if="item?.extension=='csv'" :content="item?.content" :delimiter="','" @submit="(content) => uploadSubmit(content)"/>
        <TableView v-else-if="item?.extension=='tsv'" :content="item?.content" :delimiter="'\t'" @submit="(content) => uploadSubmit(content)"/>
        <TextCell v-else-if="item?.extension=='txt' || item?.extension=='json'" :content="item?.content" @submit="(content) => {uploadSubmit(content)}"/>
        <pre v-else>
            Error: Unsupported type {{ item?.extension }}
            Types are csv, tsv, txt, json
        </pre>
    </div>
</template>

<style>

</style>
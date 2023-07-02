<script lang="ts">
import { defineComponent } from 'vue';
import Folder from '../MyFiles_Components/Folder.vue';
import {Types} from '../../types'
import { label } from '@/tailwindClasses';
    export default defineComponent ({
        data() {return {
            label
        }},
        props: {
            data: Types.Folder
        },
        components: {
            Folder
        }
    })
</script>

<template>
    <h4 :class=label>Result</h4>
    <Folder :folder="data"/>
</template>